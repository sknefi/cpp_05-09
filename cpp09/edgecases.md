# CPP09 Edge Cases (ex00 + ex01)

## ex00 — BitcoinExchange

### Header handling
- Input must start with `date | value` (trimmed).
- Any other header → `Error: bad input => <token>`.

### Date validation
- Bad date format or invalid calendar date:
  - `2001-42-42 | 2`
  - `2011-02-29 | 1` (non‑leap year)
- Expected: `Error: bad input => 2001-42-42` (only the date token).

### Malformed line
- Missing delimiter or malformed line:
  - `2011-01-03  7`
- Expected: `Error: bad input => 2011-01-03  7` (no `|`, full line).

### Value validation
- Non‑numeric value:
  - `2011-01-03 | abc`
  - Expected: `Error: bad input => 2011-01-03`
- Negative value:
  - `2012-01-11 | -1`
  - Expected: `Error: not a positive number.`
- Too large value (> 1000):
  - `2011-01-03 | 1000.0001`
  - `2012-01-11 | 2147483648`
  - Expected: `Error: too large a number.`

### Lookup rules
- If date not found, use the closest earlier date in DB.
- If date is earlier than the earliest DB date → treat as bad input.

### Output format
- `YYYY-MM-DD => value = result`

### File error
- Missing/unreadable input file:
  - `could not open file.` (exact punctuation)

## ex01 — RPN

### Operator arity
- Operator requires **at least 2** operands.
- Valid: `1 2 3 + +` → `6`
- If stack size < 2 when an operator appears → `Error: Invalid expression`

### Division by zero
- `1 0 /` → `Error: Division by zero`

### Invalid character
- `1 2 a +` → `Error: Invalid character`

### Final stack size
- Must end with **exactly one** value.
- `1 2` → `Error: Invalid expression`
- `1 2 +` → OK (single result)
CPP09 Edge Cases (ex00 + ex01)

## ex02 - Ford-Jhonson Algorithm

### Test MacOS
``` bash
./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
```

### Test Linux
```bash
./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
```

### Get count of comparisions
```bash
./PmergeMe $(shuf -i 1-1000 -n 21) 2>&1 | grep -c '^\[cmp\]'
```
2>&1 because all debugs are in cerr (standard error)

