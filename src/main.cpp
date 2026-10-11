name: Build SafeMode

on:
  push:
    branches: [main]
  workflow_dispatch:

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout
        uses: actions/checkout@v4

      - name: Build Android64
        uses: geode-sdk/build-geode-mod@main
        with:
          target: Android64

      - name: Upload artifacts
        uses: actions/upload-artifact@v4
        with:
          name: SafeMode-Build
          path: build/*.geode
