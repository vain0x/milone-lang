// Runtime code for C programs generated by the milone-lang compiler.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
  char* str;
  int len;
};

int int_cmp(int l, int r) {
  if (l == r) return 0;
  if (l < r) return -1;
  return 1;
}

int int_clamp(int x, int l, int r) {
  if (x < l) return l;
  if (x > r) return r;
  return x;
}

int str_cmp(struct String left, struct String right) {
  return strcmp(left.str, right.str);
}

struct String str_add(struct String left, struct String right) {
  if (left.len == 0 || right.len == 0) {
    return right.len == 0 ? left : right;
  }
  int len = left.len + right.len;
  char* str = (char*)malloc((len + 1) * sizeof(char));
  strcpy(str, left.str);
  strcpy(str + left.len, right.str);
  return (struct String){.str = str, .len = len};
}

struct String str_slice(struct String s, int l, int r) {
  l = int_clamp(l, 0, s.len);
  r = int_clamp(r + 1, l, s.len);
  int len = r - l;
  char* str;
  if (r == s.len) {
    str = s.str + l;
  } else {
    str = (char*)malloc((len + 1) * sizeof(char));
    strncpy(str, s.str + l, len);
    str[len] = '\0';
  }
  return (struct String){.str = str, .len = len};
}

int str_to_int(struct String s) {
  return atoi(s.str);
}

struct String str_of_int(int value) {
  char* str = (char *)calloc(20, sizeof(char));
  sprintf(str, "%d", value);
  return (struct String){.str = str, .len = strlen(str)};
}

struct String str_of_char(char value) {
  char* str = (char *)calloc(2, sizeof(char));
  str[0] = value;
  return (struct String){.str = str, .len = strlen(str)};
}

void milone_assert(int cond) {
  if (!cond) {
    exit(1);
  }
}

struct String file_read_all_text(struct String file_name) {
  FILE *fp = fopen(file_name.str, "r");
  if (!fp) {
    fprintf(stderr, "File '%s' not found.", file_name.str);
    abort();
  }

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  if (size < 0) {
    fclose(fp);
    fprintf(stderr, "%s", "Couldn't retrieve the file size.");
    abort();
  }
  fseek(fp, 0, SEEK_SET);

  char *content = (char *)calloc((size_t)size + 1, sizeof(char));
  size_t read_size = fread(content, 1, (size_t)size, fp);
  if (read_size != (size_t)size) {
    fclose(fp);
    fprintf(stderr, "%s", "Couldn't retrieve the file contents");
    abort();
  }

  fclose(fp);
  return (struct String){.str = content, .len = size};
}

int file_write_all_text(struct String file_name, struct String content) {
  FILE *fp = fopen(file_name.str, "w");
  if (!fp) {
    fprintf(stderr, "File '%s' not found.", file_name.str);
    abort();
  }

  fprintf(fp, "%s", content.str);

  fclose(fp);
  return 0;
}

int scan_int(int _dummy) {
  int value;
  int _n = scanf("%d", &value);
  return value;
}

char scan_char(int _dummy) {
  char value;
  int _n = scanf("%c", &value);
  return value;
}

struct String scan_str(int capacity) {
  if (capacity <= 0) {
    fprintf(stderr, "scan_str(%d)", capacity);
    exit(1);
  }

  char *str = calloc(capacity, sizeof(char));
  if (str == NULL) {
    fprintf(stderr, "scan_str(%d) out of memory", capacity);
    exit(1);
  }

  char fmt[16] = {};
  sprintf(fmt, "%%%ds", capacity);
  assert(fmt[15] == 0);

  int _n = scanf(fmt, str);

  int len = strlen(str);
  assert(len < capacity);
  return (struct String){.str = str, .len = len};
}

int print_int(int value) {
  return printf("%d", value);
}

int print_char(char c) {
  return printf("%c", c);
}

int print_str(struct String str) {
  return printf("%s", str.str);
}

static int s_argc;
static char **s_argv;

int arg_count(int _unit) {
  return s_argc;
}

struct String arg_get(int index) {
  if (!(0 <= index && index < s_argc)) {
    abort();
  }

  char *str = s_argv[index];
  int len = strlen(str);
  return (struct String){.str = str, .len = len};
}

int main(int argc, char** argv) {
  s_argc = argc - 1;
  s_argv = argv + 1;

  int milone_main();
  return milone_main();
}

#define main milone_main
