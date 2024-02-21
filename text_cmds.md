```bash
ls -la | cat | sort > sorted_ls_shell.txt
```

```C
exec_cmd1 = constr_exec_cmd(ft_split(ft_strtok(input, "|"), ' '));
exec_cmd2 = constr_exec_cmd(ft_split(ft_strtok(NULL, "|"), ' '));
pipe_cmd1 = constr_pipe_cmd(exec_cmd1, exec_cmd2);
exec_cmd3 = constr_exec_cmd(ft_split(ft_strtok(NULL, ">"), ' '));
redir_cmd1 = constr_redir_cmd(REDIR_STDOUT, exec_cmd3, ft_split(ft_strtok(NULL, "|"), ' ')[0], O_WRONLY | O_CREAT | O_TRUNC);
pipe_cmd2 = constr_pipe_cmd(pipe_cmd1, redir_cmd1);
return (pipe_cmd2);
```

<br/>

```bash
sort <<eof > sorted.txt
```

```C
exec_cmd1 = constr_exec_cmd(ft_split(ft_strtok(input, "<"), ' '));
heredoc_cmd1 = constr_redir_cmd(HEREDOC, exec_cmd1, "eof", O_RDONLY);
redir_cmd1 = constr_redir_cmd(REDIR_STDOUT, heredoc_cmd1, "sorted.txt",  O_WRONLY | O_CREAT | O_TRUNC);
return (redir_cmd1);
```

<br/>

```bash
cat < input.txt | sort > sorted.txt
```

```C
exec_cmd1 = constr_exec_cmd(ft_split(ft_strtok(input, "<"), ' '));
redir_cmd1 = constr_redir_cmd(REDIR_STDIN, exec_cmd1, ft_split(ft_strtok(NULL, "|"), ' ')[0],  O_RDONLY);
exec_cmd2 = constr_exec_cmd(ft_split(ft_strtok(NULL, ">"), ' '));
pipe_cmd1 = constr_pipe_cmd(redir_cmd1, exec_cmd2);
redir_cmd2 = constr_redir_cmd(REDIR_STDOUT, pipe_cmd1, ft_split(ft_strtok(NULL, "|"), ' ')[0],  O_WRONLY | O_CREAT | O_TRUNC);
return (redir_cmd2);
```