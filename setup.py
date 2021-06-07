from distutils.core import setup, Extension

lzounp = Extension('lzounp',
                    sources = ['lzounpmodule.c'],
                    libraries = ['lzo2'] )

setup (name = 'Lzounp',
       version = '1.0',
       description = 'Lzo1z/y/z unpacker',
       ext_modules = [lzounp])
