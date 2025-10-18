# Sliver SetUp

```
curl https://sliver.sh/install | sudo bash
```
```
systemctl status sliver
```
- Installs server binary to `/root/sliver-server`
- Installs mingw
- Runs the server in daemon mode using systemd
- Installs client to `/usr/local/bin/sliver`
- Generates multiplayer configurations for all users with a /home directory

> Server related logs are saved to: `~/.sliver/logs/` (default log level is INFO)
> Client logs: `~/.sliver-client/sliver-client.log`

```

```
