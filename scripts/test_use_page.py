#!/usr/bin/env python3
"""Use the WebAssembly tool on the 'Use online' page of a built website.

Usage: test_use_page.py <URL of the 'Use online' page>

The tool must show up in the page without errors,
which is checked by a screenshot that is not empty.
"""
import io
import sys
import time

from PIL import Image, ImageStat
from playwright.sync_api import sync_playwright

START_TIMEOUT_SECS = 60


def main():
    url = sys.argv[1]
    errors = []
    with sync_playwright() as playwright:
        browser = playwright.chromium.launch()
        page = browser.new_page(viewport={"width": 1280, "height": 1000})
        page.on("pageerror", lambda error: errors.append(str(error)))
        page.on("console", lambda m: print(f"console: {m.text}"))
        page.goto(url)
        frame = page.locator("iframe")
        start = time.time()
        while True:
            shot = Image.open(io.BytesIO(frame.screenshot())).convert("L")
            # An empty page has (almost) no variation in its pixels
            if ImageStat.Stat(shot).stddev[0] > 10.0:
                break
            if time.time() - start > START_TIMEOUT_SECS:
                shot.save("use_page.png")
                sys.exit("The tool did not show up in time")
            time.sleep(1)
        shot.save("use_page.png")
        browser.close()
    if errors:
        sys.exit(f"Errors on the page: {errors}")
    print("The tool shows up on the page")


if __name__ == "__main__":
    main()
