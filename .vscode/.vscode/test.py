#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
INT6011 – Assignment 1
The Digital Camera Pipeline 
"""

import os
import numpy as np
from skimage import io, color, img_as_ubyte
from scipy.ndimage import convolve
import matplotlib.pyplot as plt

SUPPORTED_PATTERNS = ("RGGB", "BGGR", "GRBG", "GBRG")


class RawCameraPipeline:
    def __init__(self,
                 tiff_path: str,
                 black_level: int,
                 white_level: int,
                 wb_multipliers,
                 bayer_pattern: str = "RGGB"):
        
        self.tiff_path = tiff_path
        self.black = float(black_level)
        self.white = float(white_level)
        self.wb_mults = np.array(wb_multipliers, dtype=np.float64)

        self.pattern = bayer_pattern.upper()
        if self.pattern not in SUPPORTED_PATTERNS:
            raise ValueError(f"Unsupported Bayer pattern: {self.pattern}")

        # Buffers for intermediate results
        self.raw_image = None      
        self.linear_image = None   
        self.rgb_linear = None     
        self.rgb_srgb = None       

    # ------------------------------------------------------------------
    # Section 2: Raw Image Extraction
    # ------------------------------------------------------------------
    def load_raw_tiff(self):
        print("Step 2: Loading RAW TIFF...")
        self.raw_image = io.imread(self.tiff_path).astype(np.float64)
        
        h, w = self.raw_image.shape
        min_val = np.min(self.raw_image)
        max_val = np.max(self.raw_image)
        bpp = np.log2(max_val + 1)
        
        print(f"  Width: {w}, Height: {h}")
        print(f"  Min value: {min_val}, Max value: {max_val}")
        print(f"  Approx. bits per pixel: {bpp:.2f}")

    # ------------------------------------------------------------------
    # Section 3: Linearization
    # ------------------------------------------------------------------
    def linearize(self):
        print("Step 3: Linearization...")
        if self.raw_image is None:
            raise ValueError("Raw image not loaded.")
            
        img = (self.raw_image - self.black) / (self.white - self.black)
        self.linear_image = np.clip(img, 0, 1)

    # ------------------------------------------------------------------
    # Section 4: The Bayer Pattern
    # ------------------------------------------------------------------
    @staticmethod
    def _build_bayer_masks(h, w, pattern):
        mask_r = np.zeros((h, w), dtype=bool)
        mask_g = np.zeros((h, w), dtype=bool)
        mask_b = np.zeros((h, w), dtype=bool)
        
        if pattern == "RGGB":
            mask_r[0::2, 0::2] = True
            mask_g[0::2, 1::2] = True
            mask_g[1::2, 0::2] = True
            mask_b[1::2, 1::2] = True
        elif pattern == "BGGR":
            mask_b[0::2, 0::2] = True
            mask_g[0::2, 1::2] = True
            mask_g[1::2, 0::2] = True
            mask_r[1::2, 1::2] = True
        elif pattern == "GRBG":
            mask_g[0::2, 0::2] = True
            mask_r[0::2, 1::2] = True
            mask_b[1::2, 0::2] = True
            mask_g[1::2, 1::2] = True
        elif pattern == "GBRG":
            mask_g[0::2, 0::2] = True
            mask_b[0::2, 1::2] = True
            mask_r[1::2, 0::2] = True
            mask_g[1::2, 1::2] = True
            
        return mask_r, mask_g, mask_b

    # ------------------------------------------------------------------
    # Section 5: White Balancing
    # ------------------------------------------------------------------
    def white_balance(self, method='camera', manual_region=None):
        print(f"Step 4: White Balancing ({method})...")
        if self.linear_image is None:
            raise ValueError("Image must be linearized first.")
        
        img = self.linear_image.copy()
        h, w = img.shape
        
        mask_r, mask_g, mask_b = self._build_bayer_masks(h, w, self.pattern)
        
        s_r, s_b = 1.0, 1.0
        
        if method == 'white_world':
            s_r = np.max(img[mask_g]) / np.max(img[mask_r])
            s_b = np.max(img[mask_g]) / np.max(img[mask_b])
            
        elif method == 'gray_world':
            s_r = np.mean(img[mask_g]) / np.mean(img[mask_r])
            s_b = np.mean(img[mask_g]) / np.mean(img[mask_b])
            
        elif method == 'camera':
            s_r = self.wb_mults[0] / self.wb_mults[1]
            s_b = self.wb_mults[2] / self.wb_mults[1]
            
        elif method == 'manual':
            if manual_region is None:
                raise ValueError("Manual method requires manual_region=(y1, y2, x1, x2)")
            y1, y2, x1, x2 = manual_region
            patch = img[y1:y2, x1:x2]
            
            p_mask_r = mask_r[y1:y2, x1:x2]
            p_mask_g = mask_g[y1:y2, x1:x2]
            p_mask_b = mask_b[y1:y2, x1:x2]
            
            s_r = np.mean(patch[p_mask_g]) / np.mean(patch[p_mask_r])
            s_b = np.mean(patch[p_mask_g]) / np.mean(patch[p_mask_b])
        else:
            raise ValueError(f"Unknown white balance method: {method}")
            
        img[mask_r] *= s_r
        img[mask_b] *= s_b
        
        self.linear_image = np.clip(img, 0, 1)
    
    # ------------------------------------------------------------------
    # Section 6: Demosaicing (Bilinear Interpolation)
    # ------------------------------------------------------------------
    def demosaic_bilinear(self):
        print("Step 5: Demosaicing (Bilinear)...")
        h, w = self.linear_image.shape
        mask_r, mask_g, mask_b = self._build_bayer_masks(h, w, self.pattern)
        
        R = self.linear_image * mask_r
        G = self.linear_image * mask_g
        B = self.linear_image * mask_b
        
        # Kernel for green channel (cross)
        kernel_G = np.array([[0, 1, 0],
                             [1, 4, 1],
                             [0, 1, 0]]) / 4.0
                             
        # Kernel for red and blue channels (includes diagonals)
        kernel_RB = np.array([[1, 2, 1],
                              [2, 4, 2],
                              [1, 2, 1]]) / 4.0

        G_full = convolve(G, kernel_G, mode='mirror')
        R_full = convolve(R, kernel_RB, mode='mirror')
        B_full = convolve(B, kernel_RB, mode='mirror')

        self.rgb_linear = np.stack((R_full, G_full, B_full), axis=-1)

    # ------------------------------------------------------------------
    # Section 7: Color Space Correction
    # ------------------------------------------------------------------
    def color_space_correction(self, M_xyz_to_cam: np.ndarray):
        print("Step 6: Color Space Correction...")
        
        M_srgb_to_xyz = np.array([
            [0.4124564, 0.3575761, 0.1804375],
            [0.2126729, 0.7151522, 0.0721750],
            [0.0193339, 0.1191920, 0.9503041]
        ])
        
        M_srgb_to_cam = M_xyz_to_cam @ M_srgb_to_xyz
        M_cam_to_srgb = np.linalg.inv(M_srgb_to_cam)
        
        # Reshape to (N, 3) for easy dot product
        flat_img = self.rgb_linear.reshape(-1, 3)
        flat_srgb = flat_img @ M_cam_to_srgb.T
        
        self.rgb_linear = np.clip(flat_srgb.reshape(self.rgb_linear.shape), 0, 1)

    # ------------------------------------------------------------------
    # Section 8: Brightness and Gamma Encoding
    # ------------------------------------------------------------------
    def brightness_and_gamma(self, target_mean: float = 0.25):
        print("Step 7: Brightness & Gamma Encoding...")
        
        # 1. Brightness Scaling
        grayscale = color.rgb2gray(self.rgb_linear)
        current_mean = np.mean(grayscale)
        scale_factor = target_mean / current_mean
        
        scaled_rgb = np.clip(self.rgb_linear * scale_factor, 0, 1)
        
        # 2. Gamma Encoding
        mask_low = scaled_rgb <= 0.0031308
        mask_high = ~mask_low
        
        self.rgb_srgb = np.zeros_like(scaled_rgb)
        self.rgb_srgb[mask_low] = 12.92 * scaled_rgb[mask_low]
        self.rgb_srgb[mask_high] = 1.055 * (scaled_rgb[mask_high] ** (1 / 2.4)) - 0.055
        self.rgb_srgb = np.clip(self.rgb_srgb, 0, 1)

    # ------------------------------------------------------------------
    # Section 9: Compression
    # ------------------------------------------------------------------
    def save_png_jpeg(self, prefix: str, quality: int = 95):
        print("Step 8: Saving Compressed Images...")
        img_8bit = img_as_ubyte(self.rgb_srgb)
        
        png_path = f"{prefix}.png"
        jpg_path = f"{prefix}.jpg"
        
        io.imsave(png_path, img_8bit)
        io.imsave(jpg_path, img_8bit, quality=quality)
        
        png_size = os.path.getsize(png_path) / 1024
        jpg_size = os.path.getsize(jpg_path) / 1024
        
        print(f"  PNG Size: {png_size:.2f} KB")
        print(f"  JPEG Size: {jpg_size:.2f} KB (Quality: {quality})")
        print(f"  Compression Ratio: {png_size / jpg_size:.2f}")
    
    def show(self, title="Final Developed Image"):
        if self.rgb_srgb is None:
            raise RuntimeError("Call brightness_and_gamma() first.")
        plt.figure(figsize=(6, 6))
        plt.imshow(self.rgb_srgb)
        plt.axis("off")
        plt.title(title)
        plt.show()


if __name__ == "__main__":
    BLACK = 2047          
    WHITE = 15000      
    WB_MULTS = [2.1, 1.0, 1.5, 1.0]   

    BAYER_PATTERN = "RGGB"

    M_XYZ_CAM = np.array([
        [6722,  -635,  -963],
        [-4287, 12460,  2028],
        [ -908,  2162,  5668]
    ], dtype=np.float64) / 10000.0

    pipeline = RawCameraPipeline(
        tiff_path="campus.tiff",
        black_level=BLACK,
        white_level=WHITE,
        wb_multipliers=WB_MULTS,
        bayer_pattern=BAYER_PATTERN
    )
    # Once you implement each step, uncomment these lines one by one to test.
    pipeline.load_raw_tiff()
    pipeline.linearize()
    pipeline.white_balance(method="camera")   # or "gray_world", "white_world", "manual"
    pipeline.demosaic_bilinear()
    pipeline.color_space_correction(M_XYZ_CAM)
    pipeline.brightness_and_gamma()
    pipeline.save_png_jpeg("campus_output", quality=95)
    pipeline.show()
