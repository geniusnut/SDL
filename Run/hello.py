
# -*- coding=utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf8')
def ConvertCN(s):  
	return s.encode('gb18030') 
print (ConvertCN("fdÄã"))