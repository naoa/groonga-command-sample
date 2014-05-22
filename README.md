# Sample groonga command

## Install

Install libgroonga-dev.

Build this command.

    % ./configure
    % make
    % sudo make install

## Usage

Register `commands/echo`:

    % groonga DB
    > register commands/echo

Now, you can use `echo` command

    > echo "hello world"
    [
      [
        0,
        0.0,
        0.0
      ],
      [
        "hello world",
        11
      ]
    ]

## License

Public domain. You can copy and modify this project freely.
