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

This project uses [moonmake](https://github.com/ranon-rat/moonmake), a lightweight Python-based build system for C++ projects.
```bash
# Build the project
py build.py

# Run the executable
./.moonmake/bin/distribution.exe
```

## Training Data

The current implementation uses text from [Xenosystems by Nick Land](https://www.amazon.com/-/es/Xenosystems-Nick-Land/dp/B0FGGG8J9B/ref=sr_1_1?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&sr=8-1) as training data.

To use your own data, you'll need to pre-process it into the `.tokens` format expected by the parser.

## How It Works

1. **Token History**: Maintains a deque of recently used tokens with their weights and possible next tokens
2. **Look-ahead Prediction**: For each token in history, predicts several steps ahead to find likely continuations
3. **Weighted Selection**: Combines predictions from all historical tokens with exponential decay based on distance
4. **Diversity Mixing**: Adds uniform noise to prevent deterministic loops

## Algorithm Details

The generator uses a sophisticated selection mechanism:

- Each previously used token contributes to predicting the next token
- Look-ahead depth decreases with token age (more recent = deeper look-ahead)
- Weights decay exponentially based on prediction distance
- Small uniform distribution is mixed in to ensure exploration

## Future Plans

This prototype serves as a foundation for:
- More sophisticated language modeling experiments
- Hybrid statistical/neural approaches
- Custom text generation applications
- Integration with modern NLP techniques

## Contributing

This is currently a research prototype. Feedback and suggestions welcome!