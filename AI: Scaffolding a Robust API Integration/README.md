# AI: Scaffolding a Robust API Integration

## Overview
This task demonstrates the use of Contextual Prompting to refactor a Python sentiment analysis script (`sentiment_analyzer.py`). The updates include secure API key handling via environment variables, Bearer token header authentication, and robust, specific exception handling for timeouts and connection errors.

## Files
- `sentiment_analyzer_initial.py`: The original initial codebase.
- `sentiment_analyzer.py`: The refactored production-ready version with enhanced security and error handling.

## Execution
To run the script locally:
```bash
export TEXT_PROCESSING_API_KEY="your_api_key_here"
python3 sentiment_analyzer.py "This is a wonderful lab assignment!"
