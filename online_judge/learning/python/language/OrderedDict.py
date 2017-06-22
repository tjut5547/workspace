# -*- coding: utf-8 -*-

"""有序字典"""

from collections import OrderedDict

regular_dict = {}
regular_dict['c'] = "tangzhoulin"
regular_dict['b'] = 'zhangjian'
regular_dict['a'] = 'zhanganyuan'
for k, v in regular_dict.items():
	print (k, v)


ordered_dict = OrderedDict()
ordered_dict['c'] = "tangzhoulin"
ordered_dict['b'] = 'zhangjian'
ordered_dict['a'] = 'zhanganyuan'
for k, v in ordered_dict.items():
	print (k, v)