SET PERL_EXE=perl.exe
SET CRYPTO_DIR=C:\Src\Harlinn.Windows\3rdParty\Harlinn.boringssl\src\crypto
%PERL_EXE% %CRYPTO_DIR%/chacha/asm/chacha-x86_64.pl nasm %CRYPTO_DIR%/asm/chacha-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/cipher_extra/asm/aes128gcmsiv-x86_64.pl nasm %CRYPTO_DIR%/asm/aes128gcmsiv-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/cipher_extra/asm/chacha20_poly1305_x86_64.pl nasm %CRYPTO_DIR%/asm/chacha20_poly1305_x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/modes/asm/aesni-gcm-x86_64.pl nasm %CRYPTO_DIR%/asm/aesni-gcm-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/aes/asm/aesni-x86_64.pl nasm %CRYPTO_DIR%/asm/aesni-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/modes/asm/ghash-ssse3-x86_64.pl nasm %CRYPTO_DIR%/asm/ghash-ssse3-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/modes/asm/ghash-x86_64.pl nasm %CRYPTO_DIR%/asm/ghash-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/md5/asm/md5-x86_64.pl nasm %CRYPTO_DIR%/asm/md5-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/ec/asm/p256-x86_64-asm.pl nasm %CRYPTO_DIR%/asm/p256-x86_64-asm.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/ec/asm/p256_beeu-x86_64-asm.pl nasm %CRYPTO_DIR%/asm/p256_beeu-x86_64-asm.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/rand/asm/rdrand-x86_64.pl nasm %CRYPTO_DIR%/asm/rdrand-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/bn/asm/rsaz-avx2.pl nasm %CRYPTO_DIR%/asm/rsaz-avx2.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/sha/asm/sha1-x86_64.pl nasm %CRYPTO_DIR%/asm/sha1-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/sha/asm/sha512-x86_64.pl nasm %CRYPTO_DIR%/asm/sha256-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/sha/asm/sha512-x86_64.pl nasm %CRYPTO_DIR%/asm/sha512-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/aes/asm/vpaes-x86_64.pl nasm %CRYPTO_DIR%/asm/vpaes-x86_64.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/bn/asm/x86_64-mont5.pl nasm %CRYPTO_DIR%/asm/x86_64-mont5.asm
%PERL_EXE% %CRYPTO_DIR%/fipsmodule/bn/asm/x86_64-mont.pl nasm %CRYPTO_DIR%/asm/x86_64-mont.asm