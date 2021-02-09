# pb_crawler
[![Build status](https://ci.appveyor.com/api/projects/status/6709v06me3dg934x/branch/master?svg=true)](https://ci.appveyor.com/project/balQu/pb-crawler/branch/master)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/1d6e9c26e17d49f4a0a448d17f2ad0ff)](https://www.codacy.com/gh/balQu/pb_crawler/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=balQu/pb_crawler&amp;utm_campaign=Badge_Grade)

Pastebin Crawler

A little tool to crawl the 50 recent pastebin pastes (www.pastebin.com/archive).

For example usage look [here](pb_crawler/example_usage.cpp).

Currently it will get the following data from each paste:
-   paste id
-   paste title
-   elapsed time (time difference between getting the paste and when the paste was posted)
-   paste language
-   paste content

In order to get this work you have to include cURL (libcurl) to this project.
The Visual Studio project is set up that it searches the .lib and .dll files under the path
"$(ProjetDir)\external\cURL_binary\\$(Configuration)".

For example, if using Debug configuration:
"$(ProjectDir)\external\cURL_binary\Debug".

The source of cURL will be searched in "pb_crawler_git\external\curl".

You have to compile cURL with SSL.
