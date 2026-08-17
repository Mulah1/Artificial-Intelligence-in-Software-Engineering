# Task: AI Pre-processor Co-pilot

## Overview
This task explores using AI as a **Macro Safety Inspector** and **Conditional Code Generator** to detect, fix, and scale C preprocessor code safely while avoiding common macro pitfalls (operator precedence, multiple evaluations, missing header guards).

## Files Included
* `flawed_macro.c`: Initial C implementation containing a flawed arithmetic macro `SQUARE(x)` prone to precedence and side-effect errors.
* `refactored_macro.c`: Safe version of `SQUARE(x)` alongside robust `#ifndef` include guards and a multi-level conditional `LOG_DEBUG` macro.
* `README.md`: Documentation for the task setup, AI workflow, and tool usage.

## AI Tools Used
* **AI Model:** Gemini / ChatGPT
* **Role assigned:** Senior C Developer and Preprocessor Safety Inspector.
