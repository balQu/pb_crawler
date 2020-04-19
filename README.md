# pb_crawler
Pastebin Crawler

In order to get this work you have to include cURL (libcurl) to this project.
The Visual Studio project is set up that it searches the .lib and .dll files under the path
"pb_crawler_git\external\cURL_binary\$(Configuration)".

For example, if using Debug configuration:
"pb_crawler_git\external\cURL_binary\Debug".

The source of cURL will be searched in "pb_crawler_git\external\curl-7.69.1".

You have to compile cURL with SSL.
