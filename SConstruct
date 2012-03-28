srcTopDir = '/home/shuai.li/shrek'
env = Environment(CPPPATH=[srcTopDir])
Export('env')
for subdir in ['base']:
    SConscript('%s/SConscript'%subdir, variant_dir='build')