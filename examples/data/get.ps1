$client = New-Object System.Net.WebClient
$url = "http://goforcode.com/download/ard.ts"
$path = "ard.ts"
$client.DownloadFile($url, $path)