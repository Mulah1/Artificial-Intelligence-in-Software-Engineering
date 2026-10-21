#!/usr/bin/python3
"""
Sentiment Analysis Tool
Analyzes the sentiment of a given sentence using a public API.
"""
import os
import sys

import requests

API_URL = "https://api.text-processing.com/api/sentiment/"
API_KEY_ENV_VAR = "TEXT_PROCESSING_API_KEY"
REQUEST_TIMEOUT = 10  # seconds


def analyze_sentiment(text):
    """
    Analyzes the sentiment of the given text using the Text Processing API.

    The API key is read from the TEXT_PROCESSING_API_KEY environment variable
    and sent as a Bearer token in the Authorization header.

    Args:
        text (str): The sentence to analyze

    Returns:
        str: The sentiment label (positive, negative, or neutral),
             or None if the request could not be completed.
    """
    api_key = os.environ.get(API_KEY_ENV_VAR, "").strip()
    if not api_key:
        print(
            f"Configuration Error: environment variable {API_KEY_ENV_VAR} "
            "is missing or empty.",
            file=sys.stderr,
        )
        return None

    headers = {"Authorization": f"Bearer {api_key}"}
    payload = {"text": text}

    try:
        response = requests.post(
            API_URL,
            data=payload,
            headers=headers,
            timeout=REQUEST_TIMEOUT,
        )
        response.raise_for_status()  # Raises exception for 4xx/5xx status codes
        data = response.json()
        label = data.get("label", "neutral")

        # Map API response format to our desired output
        if label == "pos":
            return "positive"
        elif label == "neg":
            return "negative"
        else:
            return "neutral"

    except requests.exceptions.Timeout:
        print(
            f"Timeout Error: the server did not respond within "
            f"{REQUEST_TIMEOUT} seconds. Try again later.",
            file=sys.stderr,
        )
        return None
    except requests.exceptions.ConnectionError:
        print(
            "Connection Error: could not reach the API. "
            "Check your internet connection or the API URL.",
            file=sys.stderr,
        )
        return None
    except requests.exceptions.HTTPError as e:
        status = e.response.status_code if e.response is not None else "unknown"
        if status in (401, 403):
            print(
                f"Authentication Error (HTTP {status}): "
                "the API key was rejected. Check your key.",
                file=sys.stderr,
            )
        else:
            print(f"HTTP Error (HTTP {status}): {e}", file=sys.stderr)
        return None
    except (KeyError, ValueError) as e:
        # Must come before RequestException: in newer versions of requests,
        # a bad JSON body raises an error that is both a ValueError and a
        # RequestException.
        print(f"Invalid response format: {e}", file=sys.stderr)
        return None
    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}", file=sys.stderr)
        return None


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: ./sentiment_analyzer.py <sentence>")
        sys.exit(1)
    sentence = " ".join(sys.argv[1:])
    result = analyze_sentiment(sentence)
    if result:
        print(result)
    else:
        sys.exit(1)
