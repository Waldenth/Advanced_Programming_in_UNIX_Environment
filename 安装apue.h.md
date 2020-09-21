# 安装apue.h

1. 下载: [src.3e.tar.gz](http://www.apuebook.com/src.3e.tar.gz)
2. 解压: tar xvf src.3e.tar.gz
3. 安装相应库: sudo apt-get install libbsd-dev
4. 进入到apue.3e目录，执行: make
5. cp ./include/apue.h /usr/include/
6. cp ./lib/libapue.a /usr/local/lib/
7. 编译时链接到相应库: gcc -o 1-3 1-3.c -lapue