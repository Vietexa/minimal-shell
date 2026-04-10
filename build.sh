#!/bin/bash

 gcc src/main.c src/shell/shell.c src/parser/parser.c src/commands/commands.c src/cleanup/cleanup.c -lreadline -o shell
