https://github.com/LaurieWired/GhidraMCP

Seguir las instrucciones del readme para instalar el plugin

## Cliente MCP

```
sudo npm install -g @google/gemini-cli
```

> El cliente depende de bibliotecas de python, importante utilizar un entorno donde estas esten disponibles

- pip install "mcp[cli]"
- pip install requests

```
gemini
```

settings.json
```
{
  "mcpServers": {
    "ghidra": {
      "command": "python3",
      "args": [
        "/home/llorens/ghidra_11.4.2_PUBLIC/GhidraMCP-release-1-4/bridge_mcp_ghidra.py",
        "--ghidra-server",
        "http://127.0.0.1:8080/"
      ]
    }
  }
}
```