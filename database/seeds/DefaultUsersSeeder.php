<?php

use Illuminate\Database\Seeder;
use Illuminate\Support\Facades\DB;

class DefaultUsersSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        DB::table('users')->insert([
                [
                    'name' => 'Root',
                    'email' => 'root@root.com',
                    'password' => bcrypt('root'),
                    'api_token' => 'thisisatest'
                ]
        ]);
    }
}
