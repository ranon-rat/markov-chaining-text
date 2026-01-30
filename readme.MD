# Markov Chain Text Generator

A C++ implementation of an advanced Markov chain text generator with weighted token selection and look-ahead prediction.

## Overview

This project explores probabilistic text generation using a modified Markov chain approach. Unlike traditional Markov chains that only consider the immediate previous token, this implementation:

- Maintains a history of multiple previous tokens (configurable up to 5)
- Uses weighted selection based on token frequency
- Implements look-ahead prediction to improve coherence
- Supports both character-level and word-level generation

## Features

- **Multi-token context**: Considers up to 5 previous tokens for next token prediction
- **Weighted sampling**: Selects tokens based on their frequency distribution in the training data
- **Temperature control**: Adjustable randomness in token selection (implemented but configurable)
- **Repetition avoidance**: Built-in mechanisms to prevent getting stuck in loops
- **Flexible input**: Supports both character-level and word-level tokenization

## Building
```bash
# Compile
py build.py
# Run
./.moonmake/bin/distribution.exe
```



### Configuration

Key parameters you can adjust in `main.cpp`:

- `MAX_PREVIOUS_TOKENS`: Number of previous tokens to consider (default: 5)
- `USE_WORDS`: Toggle between word and character level generation
- Generation length: Modify the loop iteration count (default: 100)
- Temperature and mixing parameters in the selection functions

## Training Data

The current implementation uses text from [Xenosystems by Nick Land](https://www.amazon.com/-/es/Xenosystems-Nick-Land/dp/B0FGGG8J9B/ref=sr_1_1?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&sr=8-1) as training data.

To use your own data, you'll need to pre-process it into the `.tokens` format expected by the parser.

## How It Works

1. **Token History**: Maintains a deque of recently used tokens with their weights and possible next tokens
2. **Look-ahead Prediction**: For each token in history, predicts several steps ahead to find likely continuations
3. **Weighted Selection**: Combines predictions from all historical tokens with exponential decay based on distance
4. **Diversity Mixing**: Adds uniform noise to prevent deterministic loops

## Future Plans

This prototype serves as a foundation for:
- More sophisticated language modeling experiments
- Hybrid statistical/neural approaches
- Custom text generation applications

## License

[Add your license here]

## Contributing

This is currently a research prototype. Feedback and suggestions welcome!