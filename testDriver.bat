cls
gcc -o bin/testDriver  parser.c token.c toString.c lexer.c symbolTable.c twinBuffer.c driver.c
bin\testDriver testcases\t5.txt testcases\out.txt