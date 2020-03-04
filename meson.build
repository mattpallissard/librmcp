project('pmon', 'c', version : '1.0.0')
cc = meson.get_compiler('c')
assert(cc.get_id() == 'clang', 'use clang only')

add_test_setup('valgrind',
    exe_wrapper : [
        'valgrind',
        '--error-exitcode=1',
        '--leak-check=full',
        '--track-origins=yes'],
    timeout_multiplier : 100)

s_dir = './src'
i_dir = './include'
inc = include_directories( i_dir )


sources = ['@0@/rmpc.c'.format(s_dir)]

test_sources = ['@0@/test.c'.format(s_dir)]

print_ping_sources= ['@0@/print_ping.c'.format(s_dir)]


librmpc = shared_library('librmpc.so', sources, include_directories : inc)
# rmpc = executable('rmpc', sources, include_directories : inc)

t = executable('t_unit', test_sources, include_directories: inc, link_with: librmpc)
print_ping = executable('print_ping', print_ping_sources, include_directories: inc, link_with: librmpc)
test('t_unit', t)
