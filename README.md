# m3u8dl-invoke
use for [cat-catch](https://github.com/xifangczy/cat-catch) extension of chrome/edge for invoking new version of [N_m3u8DL-RE](https://github.com/nilaoda/N_m3u8DL-RE)

## Usage

1. put 'N_m3u8DL-RE.exe' and 'm3u8dl-invoke.exe' in same directory.
2. modify your regedit entry for m3u8dl procotol, and register it(eg.m3u8dl-invoke.reg):  
```shell
Windows Registry Editor Version 5.00

[HKEY_CLASSES_ROOT\m3u8dl\shell\open\command]
@="\"D:\\your_path\\m3u8dl-invoke.exe\" \"%1\""
```
3. you may change parameter of N_m3u8DL-CLI in Cat-Catch extension to:  
```shell
"${url}"     --save-dir  "d:\temp\m3u8dl\result"  --tmp-dir "d:\temp\m3u8dl\download"  ${referer|exists:'--header "Referer:*"'}  --mux-after-done format=mp4   --auto-select
```