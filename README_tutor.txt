// DASH server tutorial //

1. 改server.js 的 app.listen 函式的 IP & Port
2. 把影片資料夾及MPD file放到public資料夾內
3. 改fog_index.html 內影片var url_example 的 .mpd的路徑以及 var DANE_url
4. DASH function API 使用在 src/dashplayer.js，setInitialBitrateFor，setQualityFor
5. 執行方式： # nodejs server.js
6. UE 開瀏覽器連到server ip(ex http://192.168.3.10:3000)


BBB video 4K data set:  http://www.itec.aau.at/ftp/datasets/mmsys18/
BBB video FHD data set: ftp://ftp-itec.uni-klu.ac.at/pub/datasets/mmsys12/BigBuckBunny/
DASH player API: http://cdn.dashjs.org/latest/jsdoc/module-MediaPlayer.html