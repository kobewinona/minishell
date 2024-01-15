# handling signals
ctrl-C, ctrl-D and ctrl-\

- ctrl-C displays a new prompt on a new line.
- ctrl-D exits the shell.
- ctrl-\ does nothing.

# built-in commands
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options

# execution
## structs examples
```C
typedef enum {
    CMD_EXEC,  // An executable command
    CMD_PIPE,  // A pipe between two int_cmds
    CMD_REDIR, // A command with redirection
    CMD_SEQ,   // A sequence of int_cmds
    // Add other command types as needed
} cmd_type;

typedef struct cmd {
    cmd_type type; // Type of command

    union {
        struct exec_cmd *exec; // For executable int_cmds
        struct pipe_cmd *pipe; // For pipes
        struct redir_cmd *redir; // For redirections
        struct seq_cmd *seq; // For sequences of int_cmds
        // Add other command-specific structures as needed
    };
} cmd;

typedef struct exec_cmd {
    char **argv; // Argument list
    // Add other fields as needed
} exec_cmd;

typedef struct pipe_cmd {
    cmd *left;  // Left side of the pipe
    cmd *right; // Right side of the pipe
} pipe_cmd;

typedef struct redir_cmd {
    cmd *subcmd;   // The command to apply redirection to
    char *file;    // File for redirection
    int mode;      // Redirection mode (e.g., input, output)
    int fd;        // File descriptor (e.g., STDIN, STDOUT)
} redir_cmd;

typedef struct seq_cmd {
    cmd *first; // First command in the sequence
    cmd *next;  // Next command in the sequence
} seq_cmd;
```

```C
typedef struct exec_cmd {
    char **argv; // Argument list
    // Add other fields as needed
} exec_cmd;
```

## steps to build the command tree
```bash
ls -l | grep 'value' > file.txt
```

1. Parse the Command Line:
	Break down the command line into tokens (ls, -l, |, grep, 'value', >, file.txt).

2. Construct Command Nodes:
	For each part of the command, create a corresponding command node (exec_cmd for executable commands, pipe_cmd for pipes, redir_cmd for redirections).

3. Node for ls -l:
	Create an exec_cmd node for ls -l.
	
4. Node for grep 'value':
	Create another exec_cmd node for grep 'value'.

5. Link Nodes with Pipe:
	Create a pipe_cmd node and set its left and right pointers to the ls -l and grep 'value' exec_cmd nodes, respectively.

6. Handle Redirection:
	Create a redir_cmd node for the > redirection. Set the redirection's command pointer to the pipe_cmd node, and set the file for redirection to file.txt.

7. Construct the Top-Level Command:
	The top-level cmd structure is a CMD_REDIR type, containing the redir_cmd, which in turn references the pipe_cmd.

## visualizing the command tree
```plaintext
       [redir_cmd (CMD_REDIR)]
             |
             v
          [pipe_cmd]
         /         \
        /           \
[exec_cmd for ls -l] [exec_cmd for grep 'value']
```

## execution flow
1. Start at Top-Level Node: The shell starts at the top-level redir_cmd node.

2. Handle Redirection:
	The shell prepares to redirect the output of its subcommand (the pipe_cmd node) to file.txt.

3. Execute Pipe:
	The shell then moves to the pipe_cmd node.
	It sets up a pipe in the system: the output of the left side is connected to the input of the right side.

4. Execute Left Side of Pipe:
	The shell executes the exec_cmd for ls -l.
	The output of ls -l is written to the pipe.

5. Execute Right Side of Pipe:
	The shell executes the exec_cmd for grep 'value'.
	grep reads its input from the pipe (the output of ls -l).

6. Capture Output:
	The output of grep 'value' (which is the final output of the pipe_cmd) is redirected to file.txt by the redir_cmd.
	
## execution example
```bash
ls -l | grep 'value' > file.txt
```

```plaintext
       [redir_cmd (CMD_REDIR)]
             |
             v
          [pipe_cmd]
         /         \
        /           \
[exec_cmd for ls -l] [exec_cmd for grep 'value']
```

```C
exec_cmd ls_cmd = {
    .argv = {"ls", "-l", NULL} // NULL-terminated array of arguments
};

exec_cmd grep_cmd = {
    .argv = {"grep", "value", NULL}
};

pipe_cmd pipe_between_ls_and_grep = {
    .left = (cmd *)&ls_cmd,   // Cast to cmd* for simplicity in this example
    .right = (cmd *)&grep_cmd
};

redir_cmd redirect_to_file = {
    .subcmd = (cmd *)&pipe_between_ls_and_grep, // Command being redirected
    .file = "file.txt",
    .mode = O_WRONLY | O_CREAT | O_TRUNC, // Mode for opening file: write-only, create if not exist, truncate
    .fd = STDOUT_FILENO // Standard output
};

cmd top_level_command = {
    .type = CMD_REDIR,
    .redir = &redirect_to_file // Address of the redir_cmd structure
};

// stack of execution
// ls func
// grep
// pipe func
// redir func

void runcmd(struct cmd *cmd) {
    if (cmd == NULL) {
        // Handle error: command structure is NULL
        return;
    }

    switch (cmd->type) {
    case CMD_EXEC:
        // Handle executable command
        exec_cmd(cmd->exec); // Assume exec_cmd is a function to execute exec_cmd
        break;

    case CMD_PIPE:
        // Handle pipe command
        pipe_cmd(cmd->pipe); // Assume pipe_cmd is a function to execute pipe_cmd
        break;

    case CMD_REDIR:
        // Handle redirection command
        redir_cmd(cmd->redir); // Assume redir_cmd is a function to execute redir_cmd
        break;

    case CMD_SEQ:
        // Handle sequence of int_cmds
        seq_cmd(cmd->seq); // Assume seq_cmd is a function to execute seq_cmd
        break;

    // Add cases for other command types as needed

    default:
        // Handle unknown command type
        fprintf(stderr, "Unknown command type\n");
    }
}
```

