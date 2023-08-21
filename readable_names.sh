#!/bin/bash

for name in $(grep '"name"' configuration.json | sed -e "s/            \"name\": \"\(.\+\)\",/\1/")
do
    redirected_url=$(curl -Ls -o /dev/null -w %{url_effective} "https://satisfactory-calculator.com/en/items/detail/id/$name")

    echo "$name is $(echo $redirected_url | sed -e "s#.\+\/name/\(.\+\)#\1#" | sed "s/+/ /g")"
done
