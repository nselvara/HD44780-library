#!/usr/bin/env python3

"""
Copyright 2025 Selvarajah N.

This file is part of the HD44780 LCD Library.

This library is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library. If not, see <https://www.gnu.org/licenses/>.
"""

import argparse
import os
import shutil
import subprocess
import glob

VALID_HAL = ["mock", "stub", "sim", "xilinx"]

def parse_args():
    parser = argparse.ArgumentParser(description="Configure and build HD44780 with selected HAL.")
    parser.add_argument("hal", choices=VALID_HAL, help="Select the HAL backend to use.")
    parser.add_argument("--test", action="store_true", help="Run unit tests after building.")
    parser.add_argument("--junit", action="store_true", help="Generate JUnit XML test report.")
    return parser.parse_args()

def main():
    args = parse_args()

    cmake_flags = {
        "HD44780_USE_HAL_MOCK": "OFF",
        "HD44780_USE_HAL_STUB": "OFF",
        "HD44780_USE_HAL_SIM": "OFF",
        "HD44780_USE_HAL_XILINX": "OFF"
    }
    cmake_flags[f"HD44780_USE_HAL_{args.hal.upper()}"] = "ON"

    if os.path.exists("build"):
        print("\n🔄 Cleaning previous build...\n")
        shutil.rmtree("build")

    os.makedirs("build", exist_ok=True)

    cmake_cmd = ["cmake", "-S", ".", "-B", "build"]
    for key, val in cmake_flags.items():
        cmake_cmd.append(f"-D{key}={val}")

    print("\n⚙️  Configuring with CMake:\n")
    print("   ", " ".join(cmake_cmd))
    subprocess.run(cmake_cmd, check=True)

    print("🔨 Building project...")
    subprocess.run(["cmake", "--build", "build"], check=True)

    if args.test:
        print("\n🧪 Running unit tests...\n")
        
        # Create the test command with JUnit XML output
        test_cmd = ["ctest", "--test-dir", "build", "-C", "Debug", "--output-on-failure"]
        
        # Add JUnit output if requested or in CI
        if args.junit or os.environ.get('CI') == 'true':
            junit_output = f"test-results-{args.hal}.xml"
            test_cmd.extend(["--output-junit", os.path.join(junit_output)])
            print(f"📋 JUnit report will be generated at: build/{junit_output}")
        
        # Run the tests
        subprocess.run(test_cmd, check=True)

    print(f"\n✅ Done. HAL selected: {args.hal.upper()}")

if __name__ == "__main__":
    main()
