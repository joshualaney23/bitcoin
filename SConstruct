import os
import sys
import subprocess

EnsurePythonVersion(3,6)
EnsureSconsVersion(4,1)

env = Environment(
    ENV=os.environ,
    # tools=['default', 'textfile'],
    CXXFLAGS=['-Wall', '-Wextra', '--std=c++17', '-Werror', '-Weffc++', '-g'],
    CPPPATH=['#', './include'],
    LIBS=['pthread'],
    LINKFLAGS=['-pthread']
)
env.Replace(CXX = 'clang++')

env['BTC_TOP'] = Dir('/Users/josh/Documents/Xcode Projects/bitcoin')
env['BTC_BUILD'] = env['BTC_TOP'].Dir('build')
env['BTC_LIBS'] = env['BTC_BUILD'].Dir('lib')
env['BTC_BINS'] = env['BTC_BUILD'].Dir('bin')
env['BTC_TESTS'] = env['BTC_BUILD'].Dir('tests')

env.Append(LIBPATH=Dir(env['BTC_LIBS']))

bld = Builder(action = builder_unit_test)
env.Append(BUILDERS = {'Test' : bld})

Export(['env'])

subdirs = [
    'bitcoin',
]

SConscript(dirs=subdirs)

## Aliases
env.Alias('install', 'install-lib')

env.Command('uninstall', None, Delete(FindInstalledFiles()))

env.Alias('tests', ['test-lib'])

env.Alias('runtests', ['runtests-lib'])
env.AlwaysBuild('runtests')

env.Alias('no-tests', ['lib', 'install'])

env.Default('no-tests')

env.Clean(['bin', 'lib', 'tests'], ['build'])