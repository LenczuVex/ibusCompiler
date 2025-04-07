from distutils.core import setup, Extension

def main():
    setup(name="ibusInt",
          version="1.0.0",
          description="iBusCompilerInternal",
          author="LenczuVex",
          author_email="jlenczowski@student.agh.edu.pl",
          ext_modules=[Extension("_ibus", ["ibusCompiler.cpp", "IBUS_ENCODER_DECODER/ibus.c"])])

if __name__ == "__main__":
    main()