guesses = set(open("word-bank.csv"))
answers = set(open("valid-words.csv"))

merged = guesses | answers

with open("guesses.csv", "w") as f:
    for w in sorted(merged):
        f.write(w)