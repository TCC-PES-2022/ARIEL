# ARIEL

Welcome to the ARIEL project!

ARIEL is an ARINC-615A based DataLoader application.

Here are some basics for you to build and run this project on Ubuntu 22.04:

* To build, run the following commands:

        git clone https://github.com/TCC-PES-2022/ARIEL.git
        cd ARIEL
        chmod +x setup.sh && ./setup.sh
        chmod +x make.sh && ./make.sh
        
* Before executing the application, you need to create a new user. Notice that:

    * Your username must be at least 8 characters long and must contain at least one capital letter
    * Your password must be at least 8 characters long and must contain at least one capital letter, one number and one special character 
    
    Create a new user with the followint command

        chmod +x newuser.sh && ./newuser.sh <USER_NAME> <PASSWORD>
        
* Ok, we're almost there. We now need to setup the [BLModule](https://github.com/TCC-PES-2022/BLModule.git). 
Follow the instructions on BLModule repository to build and run it.

* At last, we're ready to run ARIEL. Just run the following command:

        ./build/GUI
        
You can find images for test inside the [CommunicationManager](https://github.com/TCC-PES-2022/CommunicationManager.git) repository. Look inside `./modules/CommunicationManager/test/images` to find them.

That's it. Once you import an image and a compatibility file, you'll be able to transfer images to BLModule using the ARINC-615A protocol.
