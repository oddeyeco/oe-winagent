**OddEye Windows Agent**
---------

OddEye Agent for MS Windows is windows native metrics collection service for OddEye monitoring suite which runs on 2008 and newer versions of MS Windows.
Like OddEye Linux agent it's also OpenSourced and hosted at [**GitHUB**](https://github.com/oddeyeco/oe-winagent)
You can clone our repository and build agent yourself, or download already compiled binaries from [releases](https://github.com/oddeyeco/oe-winagent/releases) section. 
Unlike Linux Agent Windows agent supports only OddEye backend. At this moment here are no plans to support other backends, but plans may be changed at future. 

The easiest way to get OddEye agent up and running is to download compiled binaries for your Windows server and run setup.
Agent installer will ask to input your OddEye UUID, everything else can be left with it's default values. 
So before starting install procedure you need to login to [**OddEye**](https://app.oddeye.co), navigate to Personal - Profile and copy your UUID: 

![UUID](https://www.oddeye.co/documentation/images/profile0.png)

After installing Agent you will see OddEye logo next you system clock icon. Navigate your mouse to it and you will see estimated monthly cost of running current agent.

![WinCost](https://www.oddeye.co/documentation/images/wincost.png)

Right click on Icon will give options to control the Agent Service as well open containing folders and dump list of available metrics for this system. 
By default only "important" metrics are enabled, so please examine list of available metrics of current server to see if you need to enable additional ones.    

![WinOptions](https://www.oddeye.co/documentation/images/winoptions.png)
 
If yo click on **Dump Available Performance Counters**, a CSV file with names of all available performance metrics will be created in ```C:\Program Files\OddEye Agent\perf_counters_available```  
Each line contains friendly name and Performance metrics ID, You just need to copy-paste desired line to ```C:\Program Files\OddEye Agent\conf\advanced_per_counters_enabled.ini``` 
and restart agent to start collecting these performance counters. 

Windows agent is also highly configurable with reasonable defaults. 
All config files are stored as ```.ini``` files in ```C:\Program Files\OddEye Agent\conf``` directory. 
Buy changing these parameters you can monitor exactly what you need on Windows.  

After installation **OddEye Agent** agent will start with default settings. Default base settings are described in ```conf/conf.ini```

    [SelfConfig]
    check_period_seconds = 10
    log_dir= /tmp/oddeye_log
    log_rotate_seconds = 3600
    log_rotate_backups = 24
    cluster_name = testcluster
    host_group = testing
    tmpdir= /tmp/oddeye_tmp
    debug_log = False
    max_cache = 50000
    
    [TSDB]
    # --- OddEye --- #
    url = https://api.oddeye.co/oddeye-barlus/put/tsdb
    uuid = xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
    tsdtype = OddEye

We recommend to alter et least ```cluster_name = testcluster``` and ```host_group = testing``` settings and set it to your preferred values.   
It's also important to pay attention to ```check_period_seconds = 10``` and set value in accordance to your needs. 
This parameter indicates sleep interval of agent between end of sending last metric and start collection of new ones.. 

### CPU Monitoring

Location of config file is ```conf\system.ini```

    [CPU Stats]
    static_enabled=True
    percore_stats= True
    detailed_stats=True
    high=80
    severe= 95
    enabled = true

Here you can configure, if you need to monitor each of your CPU cores separately, get detailed statistics or not.
You can also enable or disable manually defined alerts and set desired thresholds, or disable this check by setting ```enabled``` to ```false```     

### Memory Monitoring

Location of config file is ```conf\system.ini```

    [Memory Stats]
    static_enabled = True
    detailed_stats = True
    high = 90
    severe = 95
    enabled = true

Provides information about servers's Memory usage.  

### HDD Monitoring

Location of config file is ```conf\system.ini```

    [Disk Stats]
    static_enabled = True
    perdisk_stats = True
    detailed_stats=True
    high = 90
    severe = 95
    enabled = True

Provides information about disk space and IO utilization. Can be configured for individual disks as well as will static defined thresholds.  

### Network and TCP 


    [Network Stats]
    detailed_stats = True
    interfaces = ALL
    enabled = True
    
    [TCP Stats]
    version = v4, v6
    enabled = false

Provide detailed or basic statistics about network usage and statistics of TCP traffic. 
If you are interested in monitoring only particular network interface, 
please copy paste its name from adapter settings as value for ```interfaces=``` so you have something like this :

    interfaces = "HP NC112i 1-port Ethernet Server Adapter"  

In this case  metrics related to only ```HP NC112i 1-port Ethernet Server Adapter``` adapter will be collected and reported. 

### GPU Monitoring

If you have GPU, this will enable collection of performance counters of your GPU device   


    [GPU Adapter Memory]
    enabled = false
    instances = ALL
    
    [GPU Engine]
    enabled = false
    instances = ALL
    
    [GPU Process Memory]
    enabled = false
    instances = ALL
    
    [RemoteFX Root GPU Management]
    enabled = false
    instances = ALL
    
    [RemoteFX Synth3D VSC VM Device]
    enabled = false

Please enable desired sections of metrics and restart the agent. 

### System etc ... 

Following are additional performance counters for fine tuned monitoring of your Servers. 

    [NUMA Node Memory]
    enabled = false
    
    [Paging File]
    enabled = false
    
    [Security System-Wide Statistics]
    enabled = false 

### Advanced Networking 

If you are running IIS, DNS, Samba, Terminal services you may be interested on monitoring these systems as well. 
Please edit ```conf\advanced_network.ini```, enable needed counters and restart agent. 

    [DNS64 Global]
    enabled = false
    
    [IPHTTPS Global]
    enabled = false
    
    [SMB Server]
    enabled = false
    
    [SMB Server Shares]
    enabled = false
    
    [Terminal Services]
    enabled = false

### Hyper-V

OddEye Agent supports out of the box Hyper-V server monitoring. Following parameters in ```conf\hyper-v.ini``` are available. 


    [Dynamic Memory Balancer]
    enabled = false
    
    [Hypervisor]
    enabled = false
    
    [Hypervisor Logical Processor]
    enabled = false
    
    [Hypervisor Root Partition]
    enabled = false
    
    [Hypervisor Root Virtual Processor]
    enabled = false
    
    [Virtual Machine Bus]
    enabled = false
    
    [Virtual Machine Health Summary]
    enabled = false
    
    [Virtual Network Adapter]
    enabled = false
    adapters = all
    
    [Virtual Storage Device]
    enabled = false
    storages = all
    
    [Virtual Switch]
    enabled = false
    switches = all
    
    [VM Vid Numa Node]
    enabled = false
    instances = all


With this you can monitor almost all aspect of **MS Hyper-V**, so if you are running **Hyper-V** just enable in config whatever counters group looks interesting and restart Agent. 

### Heartbeats

Because of the push only nature of **OddEye** our systems needs to regularly receive heartbeats from client machines. 
By getting this heartbeats **OddEye** servers knows if the client machine is up and running or it's offline, so **OddEye** can generate appropriate alert.  
Config file is ```conf/oddeye.ini``` check is enabled by default, but if you don't want us to check hosts aliveness please disable it.  

    [Self Check]
    enabled = True

### MS SQL Server Monitoring

OddEye Agent can do advanced monitoring of Microsoft SQL server.
Configuration file is  ```conf/sql_server.ini```. 
All SQL server configuration parameters are disabled by default so you should carefully enable sections which seems interesting for you . 


    [Access Methods]
    enabled = false
    
    [Availability Replica]
    enabled = false
    
    [Buffer Manager]
    enabled = false
    
    [Buffer Node]
    enabled = false
    
    [CLR]
    enabled = false
    
    [Database Replica]
    enabled = false
    
    [Databases]
    enabled = false
    databases = total
               #all
               #<database 1>, <database 1>
    
    [General Statistics]
    enabled = false
    
    [Locks]
    enabled = false
    
    [Memory Manager]
    enabled = false
    
    [Plan Cache]
    enabled = false
    
    [Query Execution]
    enabled = false
    
    [SQL Errors]
    enabled = false
    
    [SQL Statistics]
    enabled = false
    
    [Transactions]
    enabled = false
    
    [User Settable]
    enabled = false
    
    [Wait Statistics]
    enabled = false

### Utility services. 

OddEye can monitor several utility services of MS Windows OS (Printer Queue, Thermal Zone, USB). 
These performance collectors are disabled by default, if you have interest in monitoring it please edit ```conf/utility.ini``` and enable appropriate check. 

    [Print Queue]
    enabled = false
    printers = total
               #all
               #<printer 1>, <printer 2>
    
    [Thermal Zone Information]
    enabled = false
    
    [USB]
    enabled = false
    devices = all
              #<usb device 1>, <usb device 2>	
    
```printers = total``` parameter indicates that by default global print queue is monitored, but you can change it to all or set exact printer names which are interesting for monitoring.
 In USB section ```devices = all``` also  can be altered with particular USB device nam, so you can see metrics only for that particular device . 

### VMWare

Most of well known and popular Windows server products reposts their performance counters to Windows.   
**OddEye** windows agent use exactly same interface to collect any performance counter which is reported, 
This means that you can collect performance counter from most of 3-rd party product vendors. 

We have created simple plugin for monitoring VMWare on Windows . Config file is ```conf/vmware.ini```
Contains basic Memory, Disk and Network stats of VMWare. 

    [Memory Stats]
    enabled = false
    
    [Virtual Disk Stats]
    enabled = false
    
    [Network Stats]
    enabled = false


### Advanced performance counters 

As it's described above you can dump all available performance counters of running Windows OS and services to file and enable whichever counter is needed.
To do this just  edit ```conf\advanced_perf_counters_enabled.ini```, copy-paste line containing desired counter and restart agent. 

    icmp_received_timestamp_reply = \\ICMP\\Received Timestamp Reply/sec 

**Warning: Sending too much performance counters may dramatically increase budget burning rate**

Please also take a little time to read [API Guide](../barlus.md), if you plan to use home made OddEye client.