REM:Doxygenドキュメントの自動生成
echo "ドキュメントの生成中..."
doxygen Doxyfile

REM:作業ディレクトリをSourceに移動
echo "Sourceディテクトリに移動"
cd ../Source/

REM:CCCCを実行
echo "CCCCを実行中...." 
dir /b /s | cccc - 

REM:CppCheckを実行
echo "静的コード解析中...."
cppcheck --enable=all 

echo ""
cd ../../Bin/Debug

REM:単体テストの実行
echo "WinUnitを実行中...."
WinUnit NyxUnitTest.dll

REM:IPMessangerで通知