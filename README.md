# my_library
A simple library management console program created by Lawrence Williams.

Can be run with
`docker build -t my_library .`
`docker run --rm -it --link <db_container>:mydb --env-file .env my_library ./library <command with args>`
