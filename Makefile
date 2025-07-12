# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisaev <aisaev@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/26 17:33:09 by aisaev            #+#    #+#              #
#    Updated: 2025/05/15 16:48:15 by aisaev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./includes -I ./libft/includes
LDFLAGS = -L./libft -lft
RM = rm -f

# Folders
SRC_DIR = ./src
OBJ_DIR = ./build
INCLUDE_DIR = ./includes
LIBFT_DIR = ./libft

# Library file
LIBFT = $(LIBFT_DIR)/libft.a

# Executable files
CLIENT = client
SERVER = server

# Sources
CLIENT_SRCS = $(SRC_DIR)/client.c
SERVER_SRCS = $(SRC_DIR)/server.c

# Objects
CLIENT_OBJS = $(CLIENT_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SERVER_OBJS = $(SERVER_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rule by default
all: $(LIBFT) $(CLIENT) $(SERVER)

# Client compilation
$(CLIENT): $(CLIENT_OBJS)
	@$(CC) $(CLIENT_OBJS) -o $(CLIENT) $(LDFLAGS)

# Server compilation
$(SERVER): $(SERVER_OBJS)
	@$(CC) $(SERVER_OBJS) -o $(SERVER) $(LDFLAGS)

# Compilation of object files (universal)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# compilation libft files
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# clean
clean:
	@$(RM) $(CLIENT_OBJS) $(SERVER_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(CLIENT) $(SERVER)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

