# GE2338 project
This repository contains the code for the GE2338 project. It includes the generated code from different LLMs of a simple password authentication system using C to test the security performance of each model. The code is organized in separate folders for each LLM, and each folder contains the generated code for that specific model. 

## Folder structure
```
.
├── poe
│   ├── claude-opus-4.6
│   │   ├── build.sh
│   │   ├── claude-opus-4.6.c
│   │   └── credentials.txt
│   ├── gemini-3.1-pro
│   │   ├── build_self.sh
│   │   ├── credentials.txt
│   │   └── gemini-3.1-pro.c
│   ├── GLM-5
│   │   ├── build.sh
│   │   ├── glm-5.c
│   │   └── users.txt
│   └── gpt-5.4
│       ├── build.sh
│       ├── credentials.txt
│       └── gpt-5.4.c
└── README.md
```

The `poe` folder contains subfolders for each LLM (because they are called from the [Poe](https://poe.com/) platform), and each subfolder contains the generated code and a credentials file with the format suitable for the generated code. The `build.sh` script in each folder can be used to compile the C code for that specific model. The name of the subfolders and the C files indicate which LLM was used to generate the code.

Notice that `gemini-3.1-pro` does not have a `build.sh` script, but a `build_self.sh` script, which compiles and runs the code in one step. This is because the generated code for Gemini 3.1 Pro is does not contain the command to compile the code, so we need to do it manually, and the `build_self.sh` script created by ourselves help to compile and run the code.

# Testing the code
1. clone from the repository 
    ```
    git clone https://github.com/tk-wong/GE2338-project.git
    ```
2. navigate to the folder of the LLM you want to test (e.g., `cd poe/gpt-5.4`)
3. run the build script (e.g., `./build.sh` for GPT-5.4 or `./build_self.sh` for Gemini 3.1 Pro)
4. follow the prompts to enter a username and password
5. check the output to see if the authentication was successful or not. You can also check the `credentials.txt` file to see the valid username and password combinations for each model.