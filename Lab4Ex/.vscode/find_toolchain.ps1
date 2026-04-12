#!/usr/bin/env pwsh
# =============================================================
# Script tìm tự động đường dẫn toolchain của STM32CubeIDE
# Chạy: .\find_toolchain.ps1
# =============================================================

Write-Host "=== Tìm ARM GCC Toolchain ===" -ForegroundColor Cyan

# Các vị trí phổ biến CubeIDE cài
$searchRoots = @(
    "C:\ST",
    "C:\Program Files\STMicroelectronics",
    "C:\STMicroelectronics",
    "$env:USERPROFILE\ST",
    "D:\ST",
    "D:\Program Files\STMicroelectronics"
)

$gccPath = $null
$makePath = $null

foreach ($root in $searchRoots) {
    if (Test-Path $root) {
        Write-Host "Đang tìm trong: $root ..." -ForegroundColor Yellow
        
        $gcc = Get-ChildItem $root -Recurse -Filter "arm-none-eabi-gcc.exe" -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($gcc) {
            $gccPath = $gcc.FullName
            Write-Host "✅ Tìm thấy GCC: $gccPath" -ForegroundColor Green
        }
        
        $make = Get-ChildItem $root -Recurse -Filter "make.exe" -ErrorAction SilentlyContinue | Select-Object -First 1
        if ($make) {
            $makePath = $make.FullName
            Write-Host "✅ Tìm thấy Make: $makePath" -ForegroundColor Green
        }
    }
}

if (-not $gccPath) {
    Write-Host "❌ Không tìm thấy arm-none-eabi-gcc.exe" -ForegroundColor Red
    Write-Host "   Hãy mở STM32CubeIDE → Window → Preferences → MCU → Global Arm GNU Tools" -ForegroundColor Yellow
    Write-Host "   Hoặc tìm thủ công tại vị trí cài CubeIDE" -ForegroundColor Yellow
} else {
    $gccDir = Split-Path $gccPath -Parent
    $makeDir = if ($makePath) { Split-Path $makePath -Parent } else { "KHÔNG TÌM THẤY" }
    
    Write-Host ""
    Write-Host "=== Kết quả ===" -ForegroundColor Cyan
    Write-Host "GCC folder : $gccDir"
    Write-Host "Make folder: $makeDir"
    Write-Host ""
    Write-Host "=== Copy dòng này vào .vscode/settings.json ===" -ForegroundColor Cyan
    
    $gccForward = $gccDir -replace '\\', '/'
    $makeForward = $makeDir -replace '\\', '/'
    
    $pathValue = if ($makePath) {
        "${gccForward};${makeForward};" + '${env:PATH}'
    } else {
        "${gccForward};" + '${env:PATH}'
    }
    
    Write-Host @"

"terminal.integrated.env.windows": {
    "PATH": "$pathValue"
}

"@ -ForegroundColor White

    Write-Host "=== Copy dòng này vào .vscode/c_cpp_properties.json ===" -ForegroundColor Cyan
    $gccExeForward = $gccPath -replace '\\', '/'
    Write-Host @"

"compilerPath": "$gccExeForward"

"@ -ForegroundColor White
    
    # Kiểm tra make có hoạt động không
    Write-Host "=== Kiểm tra ===" -ForegroundColor Cyan
    try {
        $gccVersion = & $gccPath --version 2>&1 | Select-Object -First 1
        Write-Host "GCC: $gccVersion" -ForegroundColor Green
    } catch {
        Write-Host "Lỗi chạy GCC" -ForegroundColor Red
    }
    
    if ($makePath) {
        try {
            $makeVersion = & $makePath --version 2>&1 | Select-Object -First 1
            Write-Host "Make: $makeVersion" -ForegroundColor Green
        } catch {
            Write-Host "Lỗi chạy Make" -ForegroundColor Red
        }
    }
}
