name: Windows

on:
  push:
    branches: [ "main" ]
  pull_request:
    branches: [ "main" ]

env:
  CPM_SOURCE_CACHE: ${{ github.workspace }}/cpm_modules

jobs:
  build:
    runs-on: windows-latest

    steps:
      - uses: actions/checkout@v4
      - uses: actions/cache@v3
        with:
          path: "**/cpm_modules"
          key: ${{ github.workflow }}-cpm-modules-${{ hashFiles('**/CMakeLists.txt', '**/*.cmake') }}

      - name: Set reusable strings
        id: strings
        shell: bash
        run: |
          echo "build-output-dir=${{ github.workspace }}/build" >> "$GITHUB_OUTPUT"

      # Library configuration
      - name: Configure Library
        run: >
          cmake -B ${{ steps.strings.outputs.build-output-dir }}/library
          -DCMAKE_CXX_COMPILER=cl
          -DCMAKE_C_COMPILER=cl
          -DCMAKE_BUILD_TYPE=Debug
          -S ${{ github.workspace }}

      - name: Build Library
        run: cmake --build ${{ steps.strings.outputs.build-output-dir }}/library --config Debug

      # Standalone configuration  
      - name: Configure Standalone
        run: >
          cmake -B ${{ steps.strings.outputs.build-output-dir }}/standalone
          -DCMAKE_CXX_COMPILER=cl
          -DCMAKE_C_COMPILER=cl
          -DCMAKE_BUILD_TYPE=Debug
          -S ${{ github.workspace }}/Standalone

      - name: Build Standalone
        run: cmake --build ${{ steps.strings.outputs.build-output-dir }}/standalone --config Debug