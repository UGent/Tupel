import ROOT
import pickle

"""
Takes a directory on eos (starting from /store/...) and returns a list of all files with 'prepend' prepended
"""
#def getEOSlslist(directory, mask='', prepend='root://eoscms//eos/cms/'):
def getEOSlslist(directory, mask='',prepend='/pnfs/iihe/cms'):
    from subprocess import Popen, PIPE
    print 'looking into: '+'/pnfs/iihe/cms'+directory+'...'

#    eos_cmd = '/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select'
#    data = Popen([eos_cmd, 'ls', '/eos/cms/'+directory],stdout=PIPE)
    data = Popen(['ls','/pnfs/iihe/cms'+directory],stdout=PIPE)
    out,err = data.communicate()

    full_list = []

    ## if input file was single root file:
    if directory.endswith('.root'):
        if len(out.split('\n')[0]) > 0:
            return [prepend + directory]

    ## instead of only the file name append the string to open the file in ROOT
    for line in out.split('\n'):
        if len(line.split()) == 0: continue
#        full_list.append('/pnfs/iihe/cms' + directory + '/' + line)
        full_list.append(directory + '/' + line)

    ## strip the list of files if required
    if mask != '':
        stripped_list = [x for x in full_list if mask in x]
        return stripped_list

    ## return 
    return full_list