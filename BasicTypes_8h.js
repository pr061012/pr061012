var BasicTypes_8h =
[
    [ "AMNT_ACTION_TYPES", "BasicTypes_8h.html#a2da95afb1e16f61fa251c393729fe3a4", null ],
    [ "AMNT_CREATURE_ACTS", "BasicTypes_8h.html#a61e3f1d5a7b3881566a018d80283b26e", null ],
    [ "AMNT_CREATURE_TYPES", "BasicTypes_8h.html#ade99668a0687706f722b2b9b3f7eec62", null ],
    [ "AMNT_DET_HUM_ACTS", "BasicTypes_8h.html#a8a22ac8586bb28c52f6c39aa492f3b2b", null ],
    [ "AMNT_NONHUMANOID_TYPES", "BasicTypes_8h.html#aa617ed2c1e454c74996cd9987f3a91f4", null ],
    [ "AMNT_OBJECT_TYPES", "BasicTypes_8h.html#ab832f1efbeb4e430c55c605e2993d768", null ],
    [ "AMNT_RESOURCE_TYPES", "BasicTypes_8h.html#a9db091ba0328d7dbe79cbf907670fd89", null ],
    [ "AMNT_SHAPE_TYPES", "BasicTypes_8h.html#a631294ec44ed927aeca29878908cf102", null ],
    [ "AMNT_TOOL_TYPES", "BasicTypes_8h.html#a771820ca32ff539a53366ec23343250b", null ],
    [ "AMNT_WEATHER_TYPES", "BasicTypes_8h.html#af1a655c1dcb0060b9911d407d0904893", null ],
    [ "uint", "BasicTypes_8h.html#a91ad9478d81a7aaf2593e8d9c3d06a14", null ],
    [ "ActionError", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7", [
      [ "NO_ERROR", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7abf350750d0d4fabd8954c0f1e9bbae94", null ],
      [ "INCORRECT_INDEX", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a49dca28091c437561ce194ec6f129d71", null ],
      [ "NO_PLACE_TO_PLACE_OBJ_ON", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a40a4e5e02ce5a199f79c87cec69c2e4b", null ],
      [ "OBJ_IS_OUT_OF_RANGE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7aae5e8a11c0e323ca771a6430b8d36f32", null ],
      [ "OBJ_IS_OUT_OF_VIEW", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a7df0f4d3180b0e502cd989b1712893fb", null ],
      [ "OBJ_IS_OUT_OF_WORLD_BOUNDS", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7ae636841785f13a08bfcfc657109472df", null ],
      [ "OBJ_IS_IMMORTAL", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a377109c095e9b4290095cfa1b4865bf8", null ],
      [ "OBJ_IS_NOT_MOVABLE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7aa6288f8f48ee5ec89e7435160b198a5f", null ],
      [ "OBJ_IS_NOT_REGENERABLE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7abbf9da02803c283cc088561a261461b8", null ],
      [ "OBJ_IS_NOT_MINEABLE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a10d47f9cc859334f3438fed9815561cf", null ],
      [ "OBJ_IS_NOT_CREATABLE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a771384e51d7308ede9febd5c755825b2", null ],
      [ "OBJ_IS_NOT_PICKABLE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a569f06c27bbbad0dbb2f2d8e09f52272", null ],
      [ "OBJ_IS_NOT_IN_HEAP", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a48de155833d9c3eb81bf4d611ac56d7b", null ],
      [ "OBJ_IS_NOT_EATABLE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a3a1c5ab3ba9944b4c8eefa831120578c", null ],
      [ "OBJ_IS_STUCK", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a3a798ddd35bc4a60744b2a5165152190", null ],
      [ "OBJ_CANT_PICKUP", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a66b874d1b01b66d7d474a9ddbab2d351", null ],
      [ "OBJ_CANT_DROP", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a68af6b0a67aeb3e44a232a4ac717e74d", null ],
      [ "OBJ_CANT_EAT", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a778230853f028eb35816d2f13af0e477", null ],
      [ "OBJ_CANT_HARM", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a162a63e61e4c9ccebe466f50bc6041d4", null ],
      [ "OBJ_CANT_CREATE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7af5807eaef670512d92af8b5db39c5054", null ],
      [ "OBJ_CANT_MINE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7ac57b1f3cb5218375aa7643c34f453a21", null ],
      [ "OBJ_CANT_MOVE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a8bb0d925b1c9d0ed04105b52425b122c", null ],
      [ "OBJ_CANT_REGENERATE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a66167871bc4ffcd835f2983ac7aa5e87", null ],
      [ "OBJ_CAN_REGENERATE_ONLY_ITSELF", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a086cbe5f792a89fe72e68bf897123d2e", null ],
      [ "NOT_ENOUGH_INGREDIENTS", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a17cb1fc4e39e72cc55c82e235400b258", null ],
      [ "NOT_ENOUGH_FREE_SPACE", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7ae2a19abd177cbbd1de6ae3e9348a81c3", null ],
      [ "TOO_MANY_PARTICIPANTS", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7a64c517d0b3e51db2d35fbb919d25280c", null ],
      [ "ALL_OBJS_ARE_OUT_OF_REACH", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7ae11568d7462098ecf0529d291f3aa140", null ],
      [ "SOME_OBJS_ARE_OUT_OF_REACH", "BasicTypes_8h.html#ac3fb235cc63a1f343293ba0e8b83f9e7ab7b876badf23f59c94033e580a28964b", null ]
    ] ],
    [ "ActionState", "BasicTypes_8h.html#adc11d0d0b524594e66cd33dcc6513a3e", [
      [ "PENDING", "BasicTypes_8h.html#adc11d0d0b524594e66cd33dcc6513a3ea1869818fd53ff519eb8e429301bdff73", null ],
      [ "FAILED", "BasicTypes_8h.html#adc11d0d0b524594e66cd33dcc6513a3eaecedb56d1405a60c6069f4a0139bdec5", null ],
      [ "SUCCEEDED", "BasicTypes_8h.html#adc11d0d0b524594e66cd33dcc6513a3eac416a0ceff582d19692ee0238278f307", null ],
      [ "SUCCEEDED_WITH_ERRORS", "BasicTypes_8h.html#adc11d0d0b524594e66cd33dcc6513a3ea770a5f0ee68e10aaa475be60af854ced", null ]
    ] ],
    [ "ActionType", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950b", [
      [ "GO", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba50d8e53aac4e002d0fd296c5033ce985", null ],
      [ "MOVE", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950baed3ef32890b6da0919b57254c5206c62", null ],
      [ "MINE_OBJ", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba2e66a27a156f16bce68f9ab8d6df863a", null ],
      [ "REGENERATE_OBJ", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba9a78d084a8154debd4fe83b872f03d1f", null ],
      [ "HARM_OBJS", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba4c02ff852e43f7bbd9a3cf928798492b", null ],
      [ "CREATE_OBJ", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba11180bdd12238c960d64cfbd2f2d17ff", null ],
      [ "DROP_OBJS", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba3cf84148e5f0e4be54e30cee67546602", null ],
      [ "PICK_UP_OBJS", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba29fb3ed81fd7105b4664ad336e15a5ea", null ],
      [ "EAT_OBJ", "BasicTypes_8h.html#a21d5e8f8cdaa838586b31007df0a950ba240baad888a805c4636f763459639825", null ]
    ] ],
    [ "CreatureAction", "BasicTypes_8h.html#a5303344c79577371e13252b373606706", [
      [ "NONE", "BasicTypes_8h.html#a5303344c79577371e13252b373606706ac157bdf0b85a40d2619cbc8bc1ae5fe2", null ],
      [ "SLEEP", "BasicTypes_8h.html#a5303344c79577371e13252b373606706ad6137abebe4fdc59e2f0f2c84bdbe3fa", null ],
      [ "EAT", "BasicTypes_8h.html#a5303344c79577371e13252b373606706aefe8eeb4109392679490cf44df521c57", null ],
      [ "BUILD", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a36ea76657e6cba209d9d0a7148deef05", null ],
      [ "GATHER", "BasicTypes_8h.html#a5303344c79577371e13252b373606706ad160b6c33590f95fe8a51d6cfcd450c7", null ],
      [ "RELAX", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a8abca54580953356d3e1548ddd04a97b", null ],
      [ "EXPLORE", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a9a80539c326b5f07cbdc2c4f6c0766d9", null ],
      [ "COMMUNICATE", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a27d572ab3e817bd504ce3b47f1627630", null ],
      [ "WORK", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a08b8829a0c9899440c48b2c2affc79af", null ],
      [ "REALIZE_DREAM", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a6df69f33ea9d53566423bb7d23e6374c", null ],
      [ "ESCAPE", "BasicTypes_8h.html#a5303344c79577371e13252b373606706a0a311695a4f6c56869245418bebeb33d", null ],
      [ "REPRODUCE", "BasicTypes_8h.html#a5303344c79577371e13252b373606706af14cbd3b28e14ae7ed23756bfe852b6c", null ],
      [ "DO_NOTHING", "BasicTypes_8h.html#a5303344c79577371e13252b373606706aa3c06bc7e4d652a970cab72026c6fed1", null ]
    ] ],
    [ "CreatureType", "BasicTypes_8h.html#a5bc40f1116d89138cda8ebd1a04694df", [
      [ "HUMANOID", "BasicTypes_8h.html#a5bc40f1116d89138cda8ebd1a04694dfa2593e883617605be4584de391d2deb8b", null ],
      [ "NON_HUMANOID", "BasicTypes_8h.html#a5bc40f1116d89138cda8ebd1a04694dfaf197f84c88170597c248101eac3e4b4a", null ]
    ] ],
    [ "DetailedHumAction", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6ca", [
      [ "HUNT", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa901c4adf422bb3fb42f7aaa88bc9561a", null ],
      [ "TAKE_FOOD_FROM_INVENTORY", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caaf5f1d5e8c0f6c24906cab2803fb90007", null ],
      [ "FIND_FOOD", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caad7354b8739afca05cf7f5d5ff3ca97ea", null ],
      [ "RELAX_AT_HOME", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa4914cdcc1b5408c4e06613a2d0875620", null ],
      [ "SLEEP_AT_HOME", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa4a55cadedba0e3834fb99329e5a81831", null ],
      [ "SLEEP_ON_THE_GROUND", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa156ab19e2b28c26e7f4612fb7361a366", null ],
      [ "MINE_RESOURSES", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caacf66502bfc2b9fc8cbf63449a907fcd6", null ],
      [ "BUILD_HOUSE", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa8a456200db80fdcb92bec8dbcf8d57ec", null ],
      [ "CHOOSE_PLACE_FOR_HOME", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa0e3342ffd140d38f0b46b715aee15572", null ],
      [ "FIGHT", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa9fdcc0b679e064b5fbc7bc05bd381ac4", null ],
      [ "RUN_FROM_DANGER", "BasicTypes_8h.html#a951fdd0898192aca87aec12165cce6caa567e4a6de0c7b35c0c74f33922d31979", null ]
    ] ],
    [ "MessageType", "BasicTypes_8h.html#ac6606ebe91c8ac66a2c314c79f5ab013", [
      [ "UNDER_ATTACK", "BasicTypes_8h.html#ac6606ebe91c8ac66a2c314c79f5ab013a71ffa6e4bf89b9d4944beac486d181e0", null ]
    ] ],
    [ "NonHumanoidType", "BasicTypes_8h.html#a0b4282769c07ef55a3c2981bd98c70ec", [
      [ "COW", "BasicTypes_8h.html#a0b4282769c07ef55a3c2981bd98c70eca48505ba252c1ec37e34d882e6f4a3ecf", null ],
      [ "COW_DEMON", "BasicTypes_8h.html#a0b4282769c07ef55a3c2981bd98c70eca08e8e761112cc9d35f7b17c2e97fc77e", null ],
      [ "DRAGON", "BasicTypes_8h.html#a0b4282769c07ef55a3c2981bd98c70eca715823e7de6bbbbdd0de7fe00a9c05d6", null ]
    ] ],
    [ "ObjectType", "BasicTypes_8h.html#a842c5e2e69277690b064bf363c017980", [
      [ "RESOURCE", "BasicTypes_8h.html#a842c5e2e69277690b064bf363c017980ab65ac186b662e7e9d83c795efdbb46c4", null ],
      [ "TOOL", "BasicTypes_8h.html#a842c5e2e69277690b064bf363c017980ae19452a763ea5148b06bf3eba8d08ef6", null ],
      [ "WEATHER", "BasicTypes_8h.html#a842c5e2e69277690b064bf363c017980a8fa00ed53a162ee3eb07e179f4fc1216", null ],
      [ "BUILDING", "BasicTypes_8h.html#a842c5e2e69277690b064bf363c017980a1ae565a2eb1b9ddd41f0cefc3f33a087", null ],
      [ "CREATURE", "BasicTypes_8h.html#a842c5e2e69277690b064bf363c017980a0ae8ea0c55a461ed09a4ebe0c803d0c8", null ]
    ] ],
    [ "ResourceType", "BasicTypes_8h.html#a8571efa4409be32e28abf3ea74a0dbb1", [
      [ "WATER", "BasicTypes_8h.html#a8571efa4409be32e28abf3ea74a0dbb1a9ac7d5e5851d7a2bc186a1c3341589f6", null ],
      [ "GRASS", "BasicTypes_8h.html#a8571efa4409be32e28abf3ea74a0dbb1adbed8401e35adba25dab2e1729ee55fa", null ],
      [ "BERRIES", "BasicTypes_8h.html#a8571efa4409be32e28abf3ea74a0dbb1af2b2793b08abdd2caecb4b48cea6c444", null ],
      [ "MEAT", "BasicTypes_8h.html#a8571efa4409be32e28abf3ea74a0dbb1a762b0c1d81e03ca0afd9ffe51c31a202", null ],
      [ "TREE", "BasicTypes_8h.html#a8571efa4409be32e28abf3ea74a0dbb1a80ee3d282aa2d7af547e862568d3e240", null ]
    ] ],
    [ "ShapeType", "BasicTypes_8h.html#a5a4538eeab397888d88a4eefcc5a1345", [
      [ "CIRCLE", "BasicTypes_8h.html#a5a4538eeab397888d88a4eefcc5a1345aa79c827759ea48f0735386c4b1188911", null ],
      [ "SQUARE", "BasicTypes_8h.html#a5a4538eeab397888d88a4eefcc5a1345a4233fbf0cafb86abcee94b38d769fc59", null ]
    ] ],
    [ "SpeedType", "BasicTypes_8h.html#ae69ae616a32e1cd9040b4352defdc845", [
      [ "SLOW_SPEED", "BasicTypes_8h.html#ae69ae616a32e1cd9040b4352defdc845a053fc12e5c3618c73955e2c8ca7cb5aa", null ],
      [ "FAST_SPEED", "BasicTypes_8h.html#ae69ae616a32e1cd9040b4352defdc845aa9d1e1f7e81487c907dd97ac8ced07c2", null ]
    ] ],
    [ "ToolType", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160", [
      [ "SHOVEL", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160a21c120ba530bade9e01fbbe5f23626e2", null ],
      [ "PICKAXE", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160ade2c773ef501f2268c6b2e4f3a3389a4", null ],
      [ "HOE", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160a067001b7a28d81d13ae33b430e76cf3d", null ],
      [ "FISHING_ROD", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160a64ca2de9bf456ab98f41c09d50b595f6", null ],
      [ "BOW", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160ae5557626412a6fc8cd1120c5187203a0", null ],
      [ "SWORD", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160a498dbd887571859774972f271edfdc3c", null ],
      [ "SHIELD", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160affdd98146fb0c71b3381f94b036a100f", null ],
      [ "AXE", "BasicTypes_8h.html#a38675390df8e0ebbab2867be799b7160a7fc7bc2b5c24575b5cd0fcec2c37db09", null ]
    ] ],
    [ "WeatherType", "BasicTypes_8h.html#aae2a79ad426e847c0ddfd77d04ce2516", [
      [ "METEOR_SHOWER", "BasicTypes_8h.html#aae2a79ad426e847c0ddfd77d04ce2516a1142a5e72ceed9f7c5aa3d7fa6f93225", null ],
      [ "RAIN", "BasicTypes_8h.html#aae2a79ad426e847c0ddfd77d04ce2516a5b1b71f2b77a08a17c728a6f854a7bfe", null ],
      [ "CLOUDS", "BasicTypes_8h.html#aae2a79ad426e847c0ddfd77d04ce2516a2864a88199aef8238cc4345e675c596b", null ],
      [ "HURRICANE", "BasicTypes_8h.html#aae2a79ad426e847c0ddfd77d04ce2516a36abd3d0e25831fb6a51172f650de239", null ]
    ] ]
];