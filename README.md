# pb_crawler
Pastebin Crawler

A little tool to crawl the 50 recent pastebin pastes (www.pastebin.com/archive).

For example usage look [here](pb_crawler/example_usage.cpp).

Currently it will get the following data from each paste:
- paste id
- paste title
- elapsed time (time difference between getting the paste and when the paste was posted)
- paste language
- paste content

In order to get this work you have to include cURL (libcurl) to this project.
The Visual Studio project is set up that it searches the .lib and .dll files under the path
"$(ProjetDir)\external\cURL_binary\\$(Configuration)".

For example, if using Debug configuration:
"$(ProjectDir)\external\cURL_binary\Debug".

The source of cURL will be searched in "pb_crawler_git\external\curl".

You have to compile cURL with SSL.
