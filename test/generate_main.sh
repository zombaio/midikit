#!/bin/sh

TEST_DECL_PATTERN="^[ \t]*\(int\)[ ]\+\(test[0-9]*_[a-zA-Z0-9_]\+\)[ \t]*[(][ \t]*\(void\)\?[ \t]*[)][ ]*\([{]\|$\)"

MAIN_C="main.c"

exec >"${MAIN_C}"

echo "#include <stdio.h>"
sed "s/${TEST_DECL_PATTERN}/extern \1 \2( void );/p;d" "$@"
echo "int main(void) {"
echo "  int failures = 0;"
sed "s/${TEST_DECL_PATTERN}/  if( \2() ) { failures++; printf( \"\2 failed\\\\n\" ); } else { printf( \"\2 passed\\\\n\" ); }/p;d" "$@"
echo "  return failures;"
echo "}"

exec >&-