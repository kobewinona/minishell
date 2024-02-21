# Example 1: Heredoc with Output Redirection ✅
```bash
grep 'hello' << eof > output.txt
```
```heredoc input
hello world
this is a test
hello again
```

- Expected Result: The input output.txt should contain:
```
hello world
hello again
```

---

# Example 2: Heredoc with Pipe ✅
```bash
wc -l << eof | sort -n
```
- Expected Result: The output should be the number of lines inputted in heredoc mode, indicating the count of lines provided to wc -l, sorted numerically.

---

# Example 3: Heredoc with Append Redirection ✅
```bash
cat | sort -n << eof >> append.txt
```
```heredoc input
first line
second line
```
- Expected Result: The content is appended to the end of append.txt sorted. If append.txt did not exist before, it's created with the above content.

---

# Example 4: Heredoc with Input and Output Redirection ✅
```bash
sort < input.txt << eof > sorted_output.txt
```
- Expected Result: This is a bit tricky and might not work as intended in actual shell because the heredoc and < input.txt are conflicting for input redirection. A shell typically processes only one of these inputs, favoring < input.txt. Assuming the intent is to sort input.txt, the input sorted_output.txt should contain the sorted contents of input.txt, and the heredoc part should be ignored.

---

# Example 5: Multiple Pipes with Heredoc ✅
```bash
cat << eof | grep 'test' | wc -l
```
```heredoc input
this is a test
another line
test again
```
- Expected Result: The output should be 2, as the grep 'test' command filters two lines containing the word "test", and wc -l counts these lines.