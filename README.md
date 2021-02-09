# pb_crawler

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/02ea38e314154861a32100aeccc2e98b)](https://app.codacy.com/gh/balQu/pb_crawler?utm_source=github.com&utm_medium=referral&utm_content=balQu/pb_crawler&utm_campaign=Badge_Grade_Settings)
Branch|[![AppVeyor logo](pics/AppVeyor.png)](https://appveyor.com)
---|---
master|[![Build status](https://ci.appveyor.com/api/projects/status/6709v06me3dg934x/branch/master?svg=true)](https://ci.appveyor.com/project/balQu/pb-crawler/branch/master)

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
