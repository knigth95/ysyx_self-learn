CC=gcc
CFLAGS=-Wall -Wextra -Iinclude

# 使用 wildcard 函数查找目录中存在的 ex*.c 文件
SOURCES=$(wildcard ex[1-9].c ex[0-9][0-9].c ex90.c)

# 从源文件列表中去掉后缀 .c 替换为目标文件列表
TARGETS=$(SOURCES:.c=)

# 默认目标，编译所有存在的源文件对应的程序
all: $(TARGETS)

# 通用规则，用于从每个 exx.c 构建对应的 exx
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# 清理生成的可执行文件
clean:
	rm -f $(TARGETS)
