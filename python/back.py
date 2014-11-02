#!/usr/bin/python
import os
import time
src_dir = ['/tmp/a','/tmp/b']
dst_dir = raw_input("please input dest dir:")
comment = raw_input("please input comment:")
date = time.strftime("%Y%m%d")
now = time.strftime("%H%M%S")
if len(comment) != 0:
	now += comment
today = dst_dir+date
if not os.path.exists(today):
	os.mkdir(today)
	print 'created dir',today
target = today+'/'+now+'.tar'
tar_command = "tar -cf '%s' %s" %(target,' '.join(src_dir))
if os.system(tar_command) == 0:
	print 'successful create tar file',target
else:
	print 'create tar file failed'


