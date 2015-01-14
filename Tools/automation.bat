echo "ドキュメントの生成中..."
doxygen Doxyfile

echo "Sourceディテクトリに移動"
cd ../Nyx/Source/

echo "CCCCを実行中...." 
dir /b /s | cccc - --outdir="../../Reports/cccc"

echo "静的コード解析中...."
cppcheck --enable=all --xml . 2> ../../Reports/cppcheck/cppcheck.xml
