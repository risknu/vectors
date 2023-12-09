from __future__ import annotations

from setuptools import setup, find_packages, Extension

with open("README.md", "r") as fh:
    long_description = fh.read()

extensions = [Extension(
    "rivector.ext_library",
    sources=["rivector/src/vectors.cpp"],
    depends=["rivector/include/vectors.h"],
    include_dirs=["rivector/include"],
)]

setup(
    name='rivector',
    version='2023.1.17.1',
    author='risknu',
    ext_modules=extensions,
    author_email='risknumail@gmail.com',
    description='Fast CPython library for Vectors',
    long_description=long_description,
    long_description_content_type="text/markdown",
    packages=find_packages(),
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.11',
)
