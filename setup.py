from setuptools import setup, find_packages

setup(
    name='rivector',
    version='2023.1.15',
    author='risknu',
    author_email='risknumail@gmail.com',
    description='Fast CPython library for Vectors',
    packages=find_packages(),
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.11',
)
