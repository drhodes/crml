#! /usr/bin/env python

user = "drhodes"
repo = "crml"
label = "closed"


pre = "http://github.com/api/v2/yaml"
url = "issues/list/%s/%s/label/%s" % (user, repo, label)


print "curl " + pre + url
