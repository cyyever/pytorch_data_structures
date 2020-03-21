import os
from setuptools import setup
from torch.utils import cpp_extension

setup(
    name="cyy_pytorch_cpp",
    ext_modules=[
        cpp_extension.CppExtension(
            "cyy_pytorch_cpp",
            ["src/synced_tensor_dict.cpp"],
            include_dirs=[
                os.path.join(
                    os.path.expanduser("~"),
                    "opt",
                    "include")],
            library_dirs=[
                os.path.join(
                    os.path.expanduser("~"),
                    "opt",
                    "lib")],
            libraries=["my_cxx_lib_util"],
            # extra_compile_args=['-g']
        )],
    cmdclass={
        "build_ext": cpp_extension.BuildExtension},
)
