# Install vbox
sudo apt install virtualbox

# Install vagrant
wget -O- https://apt.releases.hashicorp.com/gpg | sudo gpg --dearmor -o /usr/share/keyrings/hashicorp-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/hashicorp-archive-keyring.gpg] https://apt.releases.hashicorp.com $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/hashicorp.list
sudo apt update && sudo apt install vagrant

# Install Vagrant plugins
vagrant plugin install vagrant-reload vagrant-vbguest winrm winrm-fs winrm-elevated

# Add some dependencies
sudo apt install sshpass lftp rsync openssh-client python3.10-venv

git clone https://github.com/Orange-Cyberdefense/GOAD.git
cd GOAD
# verify installation
./goad.sh -t check -l GOAD -p virtualbox

# install
./goad.sh -t install -l GOAD -p virtualbox

# launch goad in interactive mode
./goad.sh
